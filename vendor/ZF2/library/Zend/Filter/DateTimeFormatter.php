<?php
/**
 * Zend Framework (http://framework.zend.com/)
 *
 * @link      http://github.com/zendframework/zf2 for the canonical source repository
 * @copyright Copyright (c) 2005-2013 Zend Technologies USA Inc. (http://www.zend.com)
 * @license   http://framework.zend.com/license/new-bsd New BSD License
 */

namespace Zend\Filter;

use DateTime;

class DateTimeFormatter extends AbstractFilter
{
    /**
     * A valid format string accepted by date()
     *
     * @var string
     */
    protected $format = DateTime::ISO8601;

    /**
     * Sets filter options
     *
     * @param array|Traversable $options
     */
    public function __construct($options = null)
    {
        if ($options) {
            $this->setOptions($options);
        }
    }

    /**
     * Set the format string accepted by date() to use when formatting a string
     *
     * @param  string $format
     * @return \Zend\Filter\DateTimeFormatter
     */
    public function setFormat($format)
    {
        $this->format = $format;
        return $this;
    }

    /**
     * Filter a datetime string by normalizing it to the filters specified format
     *
     * @param  string $value
     * @throws Exception\InvalidArgumentException
     * @return string
     */
    public function filter($value)
    {
        try {
            $result = $this->normalizeDateTime($value);
        } catch (\Exception $e) {
            // DateTime threw an exception, an invalid date string was provided
            throw new Exception\InvalidArgumentException('Invalid date string provided', $e->getCode(), $e);
        }

        return $result;
    }

    /**
     * Normalize the provided value to a formatted string
     *
     * @param string|int|DateTime $value
     * @returns string
     */
    protected function normalizeDateTime($value)
    {
        if ($value === '' || $value === null) {
            return $value;
        } elseif (is_int($value)) {
            $dateTime = new DateTime('@' . $value);
        } elseif (!$value instanceof DateTime) {
            $dateTime = new DateTime($value);
        }

        return $dateTime->format($this->format);
    }
}
